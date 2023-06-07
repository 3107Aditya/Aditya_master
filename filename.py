import os

def print_file_info(folder_path):
    for file_name in os.listdir(folder_path):
        file_path = os.path.join(folder_path, file_name)
        if os.path.isfile(file_path):
            file_size = os.path.getsize(file_path)
            last_modified = os.path.getmtime(file_path)
            print("Filename:", file_name)
            print("File Size:", file_size, "bytes")
            print("Last Modified:", last_modified)
            print("Path:", file_path)
            print()

# Provide the folder path here
folder_path = '/path/to/folder'

print_file_info(folder_path)
