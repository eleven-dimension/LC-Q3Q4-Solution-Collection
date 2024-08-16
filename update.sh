#!/bin/bash

source ~/anaconda3/etc/profile.d/conda.sh
conda activate base

python track_progress.py
python generate_problems_needed_revisit.py

if git diff --quiet; then
    echo "No changes detected."
    exit 0
fi

git add ./stats/ README.md

git commit -m "Update \`problems_needed_revisit.txt\` and progress in \`README.md\`"

echo "Changes have been committed successfully."