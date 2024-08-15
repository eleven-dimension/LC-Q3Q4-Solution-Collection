import os
import re

pattern = re.compile(r'^\d{4}-[a-zA-Z]+(-[a-zA-Z]+)*$')

root_dir = './'
count = 0

for root, dirs, files in os.walk(root_dir):
    for dir_name in dirs:
        if pattern.match(dir_name):
            count += 1

print(f'progress: {count}')
