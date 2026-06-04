# Setup file for Catch2
import os
import urllib.request
import zipfile

# ==============================================================================
# Configuration
# ==============================================================================
RELEASE_VERSION = "v0.1"
BINARY_PACKAGE  = "third_party_catch2.zip"

# Standardized GitHub Release URL format
DOWNLOAD_URL = f"https://github.com/thedevmystic/mge-deps/releases/download/{RELEASE_VERSION}/{BINARY_PACKAGE}"

# Deployment Paths
TARGET_DIR = os.path.dirname(os.path.abspath(__file__))
ZIP_FILE_PATH = os.path.join(TARGET_DIR, BINARY_PACKAGE)
# ==============================================================================

def main():
    print(f"Connecting to: {DOWNLOAD_URL}")
    print(f"Downloading {BINARY_PACKAGE}...")

    try:
        # Download the binary package
        urllib.request.urlretrieve(DOWNLOAD_URL, ZIP_FILE_PATH)

        # Extract to the script's local third_party subdirectory
        print(f"Extracting package to: {TARGET_DIR}")
        with zipfile.ZipFile(ZIP_FILE_PATH, 'r') as zip_ref:
            zip_ref.extractall(TARGET_DIR)

        print("Extraction complete. Cleaning up workspace...")

    except Exception as e:
        print(f"Error: Failed to process dependency package. Details: {e}")
        if os.path.exists(ZIP_FILE_PATH):
            os.remove(ZIP_FILE_PATH)
        return

    # Delete the temporary zip archive
    if os.path.exists(ZIP_FILE_PATH):
        os.remove(ZIP_FILE_PATH)

    print(f"Dependency setup successfully completed for {BINARY_PACKAGE}!")

if __name__ == "__main__":
    main()
