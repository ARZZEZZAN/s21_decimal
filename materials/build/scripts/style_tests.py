import subprocess
import os
import sys

PATH_TO_PROJECT = '/'.join(os.path.abspath(os.path.dirname(sys.argv[0])).split('/')[:-1])
PATH_TO_CPPLINT = PATH_TO_PROJECT + '/tests/linters/cpplint.py'

devnull_stderr = sys.stdout
devnull_stdout = sys.stdout


def get_source_filenames():
    files = os.listdir(PATH_TO_PROJECT + '/src')
    arr_of_files = []
    for file in files:
        if file.find('.') != -1 and file[file.find('.') + 1] == 'c':
            arr_of_files.append(file)
    return arr_of_files


def copy_cpplint_config():
    subprocess.run(['cp', PATH_TO_PROJECT + '/tests/CPPLINT.cfg', PATH_TO_PROJECT], stdout=devnull_stdout,
                   stderr=devnull_stderr)


def delete_cpplint_config():
    subprocess.run(['rm', PATH_TO_PROJECT + '/CPPLINT.cfg'], stdout=devnull_stdout, stderr=devnull_stderr)


def style_test_result(arr_of_files):
    copy_cpplint_config()

    for i in range(len(arr_of_files)):
        result_style_test = subprocess.run(
            ['python3', PATH_TO_CPPLINT, '--extensions=c', '--quiet', PATH_TO_PROJECT + '/src/' + arr_of_files[i]],
            stderr=devnull_stderr, stdout=subprocess.PIPE, text=True)
        if len(result_style_test.stdout) != 0:
            delete_cpplint_config()
            return False

    delete_cpplint_config()
    return True


arr_of_files = get_source_filenames()
if style_test_result(arr_of_files):
    print('Style test: OK\n1')
else:
    print('Style test: FAIL\n0')
