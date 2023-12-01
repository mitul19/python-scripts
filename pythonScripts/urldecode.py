#!/usr/bin/python
import sys
import urllib.parse as ul

"""
urlencode Program.
Auther : Mitul Patel 
github : https://github.com/mitul19
Open Source Code.
"""

# take argument and print encoded output
print(ul.unquote_plus(sys.argv[1]))
