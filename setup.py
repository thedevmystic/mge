import os
import sys
import subprocess

def find_dependency_scripts(third_party_dir):
    """Recursively finds all setup.py scripts inside the third_party directory."""
    setup_scripts = []

    # Walk through the third_party directory
    for root, dirs, files in os.walk(third_party_dir):
        if "setup.py" in files:
            script_path = os.path.join(root, "setup.py")
            setup_scripts.append(script_path)

    return setup_scripts

def main():
    root_dir = os.path.dirname(os.path.abspath(__file__))
    third_party_dir = os.path.join(root_dir, "third_party")

    print("====================================================================")
    # Ensure the third_party directory actually exists
    if not os.path.exists(third_party_dir):
        print(f"Error: 'third_party/' directory not found at {third_party_dir}")
        print("Please ensure you are running this script from the MGE engine root.")
        print("====================================================================")
        return

    print("MGE Master Dependency Installer")
    print("Scanning for third-party setup scripts...")
    print("====================================================================")

    scripts = find_dependency_scripts(third_party_dir)

    if not scripts:
        print("No third-party dependency setup.py scripts found.")
        print("====================================================================")
        return

    print(f"Found {len(scripts)} dependency script(s) to process.\n")

    # Track successes and failures
    success_count = 0
    failed_scripts = []

    for script in scripts:
        rel_path = os.path.relpath(script, root_dir)
        print(f"--- Running: {rel_path} ---")

        try:
            result = subprocess.run([sys.executable, script], check=True)
            if result.returncode == 0:
                success_count += 1
        except subprocess.CalledProcessError as e:
            print(f"❌ Error execution failed for {rel_path}")
            failed_scripts.append(rel_path)

        print("-" * 40 + "\n")

    # Final Execution Summary
    print("====================================================================")
    print("Execution Summary:")
    print(f" Successfully configured: {success_count}/{len(scripts)} packages.")

    if failed_scripts:
        print("\n❌ The following scripts encountered errors:")
        for failed in failed_scripts:
            print(f"  - {failed}")
        print("\nPlease check the error outputs above and try running them individually.")
    else:
        print("\nAll third-party binaries are successfully set up and ready for CMake!")
    print("====================================================================")

if __name__ == "__main__":
    main()
