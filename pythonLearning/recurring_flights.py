from datetime import time, timedelta, datetime
import dateutil.rrule as dr
import dateutil.relativedelta as relativedelta
import pytz

from flight_duration import airports, Flight


class FlightGenerator:
    def __init__(self, flight_id, origin, destination, duration):
        self.flight_id = flight_id
        self.origin = origin
        self.destination = destination
        self.duration = duration

    def generate_flights(self, rule):
        flights = []
        for dt in rule:
            (departure_dt, arrival_dt) = self.calculate_flight_times(dt)
            flights.append(Flight(
                flight_id=self.flight_id,
                origin=self.origin,
                destination=self.destination,
                departure=departure_dt,
                arrival=arrival_dt))
        return flights

    def calculate_flight_times(self, dep):

        dep_tz = pytz.timezone(self.origin.tz)
        dep_localized = dep_tz.localize(dep, is_dst=None)
        arr_tz = pytz.timezone(self.destination.tz)
        arr_localized = (dep_localized + self.duration).astimezone(arr_tz)

        return dep, datetime.combine(arr_localized.date(), arr_localized.time())

generator = FlightGenerator(flight_id='AA123',
                            origin=airports['ATL'],
                            destination=airports['SVO'],
                            duration=timedelta(hours=13, minutes=25))

# third Monday of every month in 2018
flights = generator.generate_flights(dr.rrule(
    freq=dr.WEEKLY,
    byweekday=relativedelta.MO(3),
    dtstart=datetime(2018, 1, 1, 10, 30, 0),
    count=12
))

flights += generator.generate_flights(dr.rrule(
    freq=dr.HOURLY,
    interval=3,
    dtstart=datetime(2019, 1, 1, 15, 0, 0),
    count=3
))
flights += generator.generate_flights(dr.rrule(
    freq=dr.HOURLY,
    byhour=[10, 13],
    dtstart=datetime(2019, 2, 1, 15, 0, 0),
    until=datetime(2019, 2, 4, 15, 0, 0)
))
#TODO: more examples of relative delta

