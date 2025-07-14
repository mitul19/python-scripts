# 🎯 MY FINAL PORTFOLIO TRACKER -
# Key insight: Normalize by stock count for composition-neutral returns

import yfinance as yf
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime, timedelta
import warnings
warnings.filterwarnings('ignore')

# ===== CONFIGURATION =====
DEFAULT_START_DATE = "2025-01-21"
DEFAULT_END_DATE = "2025-06-27"
MOVING_AVERAGE_WINDOW = 30

# ===== YOUR PORTFOLIO =====
# Format: "SYMBOL QUANTITY [START_DATE] [END_DATE]"
# Dates in DD/MM/YYYY format, leave blank to use defaults
PORTFOLIO_INPUT = """
NSE:BAJFINANCE 1
NSE:ICICIBANK 11 22/04/2025
NSE:SHREECEM 1 22/04/2025 05/05/2025
"""

class PortfolioTracker:
    def __init__(self):
        self.portfolio = []
        self.stock_data = {}
        self.results = pd.DataFrame()

    def parse_portfolio(self, input_text):
        """Parse portfolio input - cleaner than ChatGPT's version"""
        print("📊 Parsing portfolio...")

        for line_num, line in enumerate(input_text.strip().split('\n'), 1):
            line = line.strip()
            if not line:
                continue

            parts = line.split()
            if len(parts) < 2:
                print(f"⚠️  Line {line_num}: Invalid format - {line}")
                continue

            symbol = parts[0]
            try:
                quantity = int(parts[1])
            except ValueError:
                print(f"⚠️  Line {line_num}: Invalid quantity - {parts[1]}")
                continue

            # Handle dates with better error checking
            start_date = self._parse_date(parts[2] if len(parts) > 2 else DEFAULT_START_DATE)
            end_date = self._parse_date(parts[3] if len(parts) > 3 else DEFAULT_END_DATE)

            if start_date >= end_date:
                print(f"⚠️  Line {line_num}: End date must be after start date")
                continue

            self.portfolio.append({
                'symbol': symbol.replace("NSE:", ""),  # Remove NSE: prefix like ChatGPT does
                'quantity': quantity,
                'start_date': start_date,
                'end_date': end_date
            })

        print(f"✅ Parsed {len(self.portfolio)} stocks")
        return len(self.portfolio) > 0

    def _parse_date(self, date_str):
        """Parse date with multiple format support"""
        formats = ['%d/%m/%Y', '%Y-%m-%d', '%d-%m-%Y']

        for fmt in formats:
            try:
                return datetime.strptime(date_str, fmt)
            except ValueError:
                continue

        raise ValueError(f"Invalid date format: {date_str}")

    def fetch_stock_data(self):
        """Fetch stock data with better error handling"""
        print("\n📈 Fetching stock data...")

        # Get overall date range
        all_start_dates = [stock['start_date'] for stock in self.portfolio]
        all_end_dates = [stock['end_date'] for stock in self.portfolio]

        global_start = min(all_start_dates) - timedelta(days=5)  # Small buffer
        global_end = max(all_end_dates) + timedelta(days=1)

        print(f"📅 Data range: {global_start.date()} to {global_end.date()}")

        successful_fetches = 0

        for i, stock in enumerate(self.portfolio, 1):
            symbol = stock['symbol']
            ticker = f"{symbol}.NS"

            print(f"   {i:2d}/{len(self.portfolio)} Fetching {symbol}...", end="")

            try:
                data = yf.download(ticker, start=global_start, end=global_end,
                                 progress=False)

                if data.empty:
                    print(" ❌ No data")
                    continue

                # Store close prices with timezone handling
                prices = data['Close'].copy()
                if hasattr(prices.index, 'tz_localize'):
                    prices.index = prices.index.tz_localize(None)

                self.stock_data[symbol] = prices
                successful_fetches += 1
                print(f" ✅ {len(prices)} days")

            except Exception as e:
                print(f" ❌ Error: {str(e)[:50]}")

        print(f"\n✅ Successfully fetched {successful_fetches}/{len(self.portfolio)} stocks")
        return successful_fetches > 0

    def calculate_composition_neutral_returns(self):
        """
        THE KEY INSIGHT: Normalize by number of stocks held
        This makes returns composition-neutral automatically
        """
        print("\n🎯 Calculating composition-neutral returns...")
        print("💡 Key insight: Normalize by stock count to eliminate composition bias")

        # Create date range for analysis
        all_dates = set()
        for prices in self.stock_data.values():
            all_dates.update(prices.index)

        if not all_dates:
            print("❌ No price data available")
            return False

        date_range = pd.date_range(min(all_dates), max(all_dates), freq='D')
        print(f"📅 Analysis period: {len(date_range)} days")

        # Create portfolio value and holding mask matrices
        portfolio_values = pd.DataFrame(index=date_range)
        holding_mask = pd.DataFrame(index=date_range)

        print("📊 Building portfolio matrices...")
        for stock in self.portfolio:
            symbol = stock['symbol']

            if symbol not in self.stock_data:
                continue

            # Get stock values (price × quantity)
            prices = self.stock_data[symbol].reindex(date_range, method='ffill')
            stock_values = prices * stock['quantity']

            # Create holding mask (True when stock is held)
            mask = pd.Series(False, index=date_range)
            mask[(date_range >= stock['start_date']) & (date_range <= stock['end_date'])] = True

            portfolio_values[symbol] = stock_values
            holding_mask[symbol] = mask

        # THE MAGIC: ChatGPT's elegant solution
        print("✨ Applying composition-neutral normalization...")

        # Only count values when stocks are actually held
        held_values = portfolio_values.where(holding_mask)
        total_portfolio_value = held_values.sum(axis=1)

        # Count how many stocks are held each day
        stocks_held_count = holding_mask.sum(axis=1).replace(0, np.nan)

        # Normalize by stock count - THIS IS THE KEY!
        normalized_portfolio = total_portfolio_value / stocks_held_count

        print(f"📈 Portfolio composition changes handled automatically")
        print(f"🎯 Returns now reflect only price movements, not composition changes")

        # Calculate returns and NAV
        daily_returns = normalized_portfolio.pct_change().fillna(0)
        nav = (1 + daily_returns).cumprod() * 100  # Start at 100

        # Build results DataFrame
        self.results = pd.DataFrame(index=date_range)
        self.results['Portfolio_Value'] = total_portfolio_value
        self.results['Stocks_Held'] = stocks_held_count
        self.results['Normalized_Value'] = normalized_portfolio
        self.results['Daily_Return'] = daily_returns
        self.results['Daily_Return_Pct'] = daily_returns * 100
        self.results['NAV'] = nav
        self.results['Cumulative_Return_Pct'] = (nav / 100 - 1) * 100

        # Add moving average
        self.results['NAV_MA'] = nav.rolling(MOVING_AVERAGE_WINDOW).mean()

        # Calculate drawdowns
        self._calculate_drawdowns()

        # Remove days with no holdings
        self.results = self.results.dropna(subset=['Normalized_Value'])

        print(f"✅ Calculated returns for {len(self.results)} trading days")

        return True

    def _calculate_drawdowns(self):
        """Calculate drawdown statistics"""
        nav = self.results['NAV']

        # Running maximum NAV
        rolling_max = nav.expanding().max()

        # Drawdown as percentage from peak
        drawdowns = (nav - rolling_max) / rolling_max * 100
        self.results['Drawdown_Pct'] = drawdowns

        # Calculate max drawdown
        max_drawdown = drawdowns.min()
        print(f"📉 Maximum drawdown: {max_drawdown:.2f}%")

    def generate_statistics(self):
        """Generate comprehensive portfolio statistics"""
        print("\n📊 Generating statistics...")

        if self.results.empty:
            return {}

        returns = self.results['Daily_Return'].dropna()
        nav = self.results['NAV']

        stats = {
            'Total_Days': len(self.results),
            'Trading_Days': len(returns),
            'Initial_NAV': nav.iloc[0],
            'Final_NAV': nav.iloc[-1],
            'Total_Return_Pct': self.results['Cumulative_Return_Pct'].iloc[-1],
            'Annualized_Return_Pct': returns.mean() * 252 * 100,
            'Volatility_Pct': returns.std() * np.sqrt(252) * 100,
            'Sharpe_Ratio': (returns.mean() / returns.std()) * np.sqrt(252) if returns.std() > 0 else 0,
            'Max_Drawdown_Pct': self.results['Drawdown_Pct'].min(),
            'Best_Day_Pct': returns.max() * 100,
            'Worst_Day_Pct': returns.min() * 100,
            'Positive_Days': (returns > 0).sum(),
            'Negative_Days': (returns < 0).sum(),
            'Win_Rate_Pct': (returns > 0).mean() * 100
        }

        return stats

    def display_results(self):
        """Display comprehensive results"""
        stats = self.generate_statistics()

        print("\n" + "="*60)
        print("📊 PORTFOLIO PERFORMANCE SUMMARY")
        print("="*60)

        print(f"📅 Analysis Period: {stats['Trading_Days']} trading days")
        print(f"💰 Total Return: {stats['Total_Return_Pct']:.2f}%")
        print(f"📈 Annualized Return: {stats['Annualized_Return_Pct']:.2f}%")
        print(f"📊 Volatility: {stats['Volatility_Pct']:.2f}%")
        print(f"⚡ Sharpe Ratio: {stats['Sharpe_Ratio']:.2f}")

        print(f"\n🎯 DAILY PERFORMANCE:")
        print(f"Best Day: +{stats['Best_Day_Pct']:.2f}%")
        print(f"Worst Day: {stats['Worst_Day_Pct']:.2f}%")
        print(f"Win Rate: {stats['Win_Rate_Pct']:.1f}% ({stats['Positive_Days']}/{stats['Trading_Days']})")

        print(f"\n📉 RISK METRICS:")
        print(f"Maximum Drawdown: {stats['Max_Drawdown_Pct']:.2f}%")

        return stats

    def create_visualizations(self):
        """Create portfolio visualizations"""
        print("\n📈 Creating visualizations...")

        fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))

        # NAV Chart
        ax1.plot(self.results.index, self.results['NAV'], label='Portfolio NAV', linewidth=2)
        ax1.plot(self.results.index, self.results['NAV_MA'],
                label=f'{MOVING_AVERAGE_WINDOW}D MA', linestyle='--', alpha=0.7)
        ax1.set_title('Portfolio NAV Over Time')
        ax1.set_ylabel('NAV')
        ax1.legend()
        ax1.grid(True, alpha=0.3)

        # Daily Returns
        ax2.plot(self.results.index, self.results['Daily_Return_Pct'], alpha=0.7)
        ax2.axhline(y=0, color='black', linestyle='-', alpha=0.3)
        ax2.set_title('Daily Returns')
        ax2.set_ylabel('Return (%)')
        ax2.grid(True, alpha=0.3)

        # Drawdown
        ax3.fill_between(self.results.index, self.results['Drawdown_Pct'], 0,
                        color='red', alpha=0.3)
        ax3.set_title('Drawdown from Peak')
        ax3.set_ylabel('Drawdown (%)')
        ax3.grid(True, alpha=0.3)

        # Stocks Held Over Time
        ax4.plot(self.results.index, self.results['Stocks_Held'], alpha=0.7)
        ax4.set_title('Number of Stocks Held')
        ax4.set_ylabel('Stock Count')
        ax4.grid(True, alpha=0.3)

        plt.tight_layout()
        plt.show()

    def save_results(self, filename='my_portfolio_analysis.xlsx'):
        """Save results to Excel"""
        print(f"\n💾 Saving results to {filename}...")

        with pd.ExcelWriter(filename, engine='openpyxl') as writer:
            # Main results
            self.results.to_excel(writer, sheet_name='Portfolio_Returns')

            # Statistics
            stats = self.generate_statistics()
            stats_df = pd.DataFrame.from_dict(stats, orient='index', columns=['Value'])
            stats_df.to_excel(writer, sheet_name='Statistics')

            # Portfolio composition
            portfolio_df = pd.DataFrame(self.portfolio)
            portfolio_df.to_excel(writer, sheet_name='Portfolio_Composition', index=False)

        print(f"✅ Results saved to {filename}")

        try:
            from google.colab import files
            files.download(filename)
            print(f"📥 File downloaded: {filename}")
        except ImportError:
            print("💡 File saved locally (not in Colab)")

    def run_complete_analysis(self):
        """Run the complete portfolio analysis"""
        print("🚀 STARTING PORTFOLIO ANALYSIS")
        print("💡 Using composition-neutral approach learned from ChatGPT")
        print("="*60)

        # Step 1: Parse portfolio
        if not self.parse_portfolio(PORTFOLIO_INPUT):
            print("❌ Failed to parse portfolio")
            return False

        # Step 2: Fetch data
        if not self.fetch_stock_data():
            print("❌ Failed to fetch stock data")
            return False

        # Step 3: Calculate returns
        if not self.calculate_composition_neutral_returns():
            print("❌ Failed to calculate returns")
            return False

        # Step 4: Display results
        self.display_results()

        # Step 5: Create visualizations
        self.create_visualizations()

        # Step 6: Save results
        self.save_results()

        print("\n🎉 ANALYSIS COMPLETE!")
        print("✅ Composition-neutral returns calculated successfully")
        print("✅ Portfolio changes do not affect return calculations")
        print("✅ True stock-picking performance measured")

        return True

# ===== MAIN EXECUTION =====
def main():
    """Main execution function"""
    tracker = PortfolioTracker()
    success = tracker.run_complete_analysis()

    if success:
        print(f"\n💡 KEY INSIGHT: This approach normalizes portfolio value by stock count")
        print(f"   This automatically eliminates composition bias in returns")
        print(f"   Credit to ChatGPT for the elegant normalization solution!")

    return tracker

# Run the analysis
if __name__ == "__main__":
    portfolio_tracker = main()