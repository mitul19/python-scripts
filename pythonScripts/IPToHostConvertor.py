import socket


def find_hostname(targeted_ip_addr, debug=False):
    try:
        targeted_hostname, aliaslist, ipaddrlist = socket.gethostbyaddr(
            targeted_ip_addr
        )
        if debug:
            print(f"aliaslist : {aliaslist}, ipaddrlist : {ipaddrlist}")
        return targeted_hostname
    except socket.herror:
        return None


input_ip_addr = input("Enter the targeted IP address : ")
hostname = find_hostname(input_ip_addr)
print(f"The hostname of targeted IP address {input_ip_addr} is {hostname}")

# Example IP = 4.2.2.2
