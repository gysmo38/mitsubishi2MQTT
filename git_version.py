import subprocess

Import("env")

def get_git_version():
    git_cmd='git describe --tags --always --dirty'
    try:
        ret = subprocess.run(git_cmd.split(), capture_output=True, text=True)
    except Exception as e:
        print(f'get_git_version: {e}')
        return None
    return ret.stdout.strip()

version = get_git_version()
if version:
    env.Append(BUILD_FLAGS = [ f'-D GIT_VERSION="{version}"' ])

