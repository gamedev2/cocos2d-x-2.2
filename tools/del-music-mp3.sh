#!/bin/bash

# Delete file from your repo
echo "====================================="
echo "Delete file from your repo"
echo "====================================="

# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_00-Tears_From_The_Moon.mp3' --prune-empty --tag-name-filter cat -- --all

# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_03-Wired.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_10-Indigo.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_12-String Tek.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_22-Scallop_Pond.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_23-Crime_Trail.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_25-Freeflight.mp3' --prune-empty --tag-name-filter cat -- --all
#  git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_02-War_Path(还行,有点怪怪的).mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_05-Darkness.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_08-Surprise Attack Drums.mp3' --prune-empty --tag-name-filter cat -- --all
#  git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_20-Lesser_Evil(太忧郁,不好).mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/01-Timeline_Choir.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/06-Kiss my Drums.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/14-Here_Comes_The_King.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/21-I_Hear_Voices.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/35-Monster_Build.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/X-Bigfoot.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/X-Cyberworld.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/X-Gregorian_Dream.mp3' --prune-empty --tag-name-filter cat -- --all

# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_02-War_Path*.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_20-Lesser_Evil*.mp3' --prune-empty --tag-name-filter cat -- --all

# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/++_12-String Tek.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/+_08-Surprise Attack Drums.mp3' --prune-empty --tag-name-filter cat -- --all
# git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/06-Kiss my Drums.mp3' --prune-empty --tag-name-filter cat -- --all

git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch projects/WoPet/Resources/music/*.mp3' --prune-empty --tag-name-filter cat -- --all
