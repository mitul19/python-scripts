import hashlib, base64
import argparse
import os

'''
Content-MD5 and Etag calculation Program.
Auther : Mitul Patel 
github : https://github.com/mitul19
'''

# Argument list, Help and input validation
parser = argparse.ArgumentParser(description="Calculate content-md5 and Etag for files")
parser.add_argument("-f", "--files", help="A list of files to process for content-md5 and etag calculation", type=argparse.FileType("rb"), nargs="*")
args = parser.parse_args()

if(args.files):
    for file in args.files:
        with open(os.path.abspath(file.name),"rb") as fp:
            content = fp.read()
        content_md5=hashlib.md5()
        content_md5.update(content)
        content_base64=base64.b64encode(content_md5.digest())
        print('Content-MD5: {} | Etag: {}  | Filename {}'.format(content_base64.decode("utf-8"), content_md5.hexdigest(), os.path.abspath(file.name)))
else:
    print(parser.print_help())
