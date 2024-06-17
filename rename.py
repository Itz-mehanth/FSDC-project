import os
import shutil

# Path to the folder containing PNG files
folder_path = 'Frames'

# List all files in the folder
files = os.listdir(folder_path)

# Filter PNG files
png_files = [file for file in files if file.lower().endswith('.png')]

# Sort PNG files based on their current names (assuming they are named alphabetically or numerically)
png_files.sort()

# Rename PNG files sequentially
for i, old_name in enumerate(png_files):
    new_name = f"{i + 1}.png"
    old_path = os.path.join(folder_path, old_name)
    new_path = os.path.join(folder_path, new_name)
    shutil.move(old_path, new_path)
    print(f'Renamed {old_name} to {new_name}')

print('Renaming complete.')
