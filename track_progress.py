import os
import re
import requests

MIN_RATING = 1900

def get_problem_number():
    url = 'https://zerotrac.github.io/leetcode_problem_rating/data.json'
    result = -1
    response = requests.get(url)
    if response.status_code == 200:
        data = response.json() 
        left, right = 0, len(data) - 1
        while left <= right:
            mid = (left + right) // 2
            if data[mid]['Rating'] > MIN_RATING:
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
    return result + 1

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
    problem_number = get_problem_number()
    lines[-1] = re.sub(r'Progress: \d+ / \d+', f'Progress: {count} / {problem_number}', lines[-1])

with open(readme_path, 'w') as file:
    file.writelines(lines)