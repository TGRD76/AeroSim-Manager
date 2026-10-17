from pathlib import Path
import subprocess
import sys
root = Path(__file__).resolve().parent
subprocess.run([sys.executable, '-m', 'ziglang', 'rc', '/fo', 'app.res', 'app.rc'], cwd=root, check=True)
subprocess.run([sys.executable, '-m', 'ziglang', 'cc', '-target', 'x86_64-windows-gnu', '-std=c11', '-O2', '-Wall', '-Wextra', '-Werror', '-municode', '-Wl,--subsystem,windows', '-Wl,--stack,33554432', 'app.c', 'app.res', '-lcomctl32', '-lshell32', '-lole32', '-lshlwapi', '-lcomdlg32', '-lgdi32', '-luxtheme', '-lmsimg32', '-o', 'AeroSim-Manager-1.0.0.exe'], cwd=root, check=True)
print('Compiled:', root / 'AeroSim-Manager-1.0.0.exe')
