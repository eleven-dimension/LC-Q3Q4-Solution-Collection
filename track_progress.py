import os
import re

pattern = re.compile(r'^\d{4}-[a-zA-Z]+(-[a-zA-Z]+)*$')

root_dir = './'
count = 0

for root, dirs, files in os.walk(root_dir):
    for dir_name in dirs:
        if pattern.match(dir_name):
            count += 1

readme_path = os.path.join(root_dir, 'README.md')
with open(readme_path, 'r') as file:
    lines = file.readlines()

if lines:
    lines[-1] = re.sub(r'Progress: \d+ / \d+', f'Progress: {count} / 576', lines[-1])

with open(readme_path, 'w') as file:
    file.writelines(lines)