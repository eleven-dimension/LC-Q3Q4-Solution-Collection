import os

root_dir = './'
results = []
for root, dirs, files in os.walk(root_dir):
    for dir_name in dirs:
        memo_path = os.path.join(root, dir_name, 'memo.md')
        if os.path.exists(memo_path):
            with open(memo_path, 'r', encoding='utf-8') as file:
                content = file.read()
                if "REVISIT NEEDED" in content:
                    results.append(dir_name)

output_file = './stats/problems_needed_revisit.txt'
os.makedirs(os.path.dirname(output_file), exist_ok=True)

with open(output_file, 'w', encoding='utf-8') as f:
    for result in results:
        f.write(result + '\n')