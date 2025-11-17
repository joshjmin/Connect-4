fs = import('fs')

tests = [
    'public/lab6-1',
    'public/lab6-2',
    'public/lab6-3',
    'public/lab6-4',
    'private/lab6-5',
    'private/lab6-6',
    'private/lab6-7',
]

foreach test : tests
    test(test, files('runner.py'), args : [test, exe.full_path()])
endforeach
