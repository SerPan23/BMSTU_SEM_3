import ctypes

lib = ctypes.CDLL('./lib/libarr.so')

# int arr_fill_fibonacci(int *arr, int size, int n);
_fill_array = lib.arr_fill_fibonacci
_fill_array.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
_fill_array.restype = ctypes.c_int

# Init array with predict size
def fill_array_1(num):
    arr = (ctypes.c_int * num)()

    rc = _fill_array(arr, num, num)

    if rc == num:
        return list(arr)
  
    return []


# Init array with value that func return
def fill_array_2(num):
    size = _fill_array(None, 0, num)

    arr = (ctypes.c_int * size)()

    rc = _fill_array(arr, size, num)

    if rc == num:
        return list(arr)

    return []


# int arr_copy_unique(int *src, int src_size, int *dst, int dst_size);
_copy_array = lib.arr_copy_unique
_copy_array.argtypes = (ctypes.POINTER(ctypes.c_int),
                        ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_copy_array.restype = ctypes.c_int


# Init array with predict size
def copy_array_1(src_list):
    src_len = len(src_list)
    src = (ctypes.c_int * src_len)(*src_list)
    arr = (ctypes.c_int * src_len)()

    rc = _copy_array(src, src_len, arr, src_len)

    return list(arr)[:rc]


# Init array with value that func return
def copy_array_2(src_list):
    src_len = len(src_list)
    src = (ctypes.c_int * src_len)(*src_list)

    size = _copy_array(src, src_len, None, 0)

    arr = (ctypes.c_int * size)()

    rc = _copy_array(src, src_len, arr, src_len)

    if rc == size:
        return list(arr)

    return []


def read_array():
    print("Enter arr size:")
    n = int(input())
    print("Enter arr data (only one num on row):")
    arr = [int(input()) for _ in range(n)]

    return arr

menu = """
Choose:
1) Fill array by fibonacci (init array by predict size)
2) Fill array by fibonacci (init array by return value from func)
3) Copy unique elements from array (init array by predict size)
4) Copy unique elements from array (init array by return value from func)
0) Exit
"""

is_running = True

while is_running:
    print(menu)
    command = int(input())
    
    if command == 0:
        is_running = False
    elif command == 1:
        print("Enter fibonacci nums count:")
        n = int(input())
        print("Result:", fill_array_1(n))

    elif command == 2:
        print("Enter fibonacci nums count:")
        n = int(input())
        print("Result:", fill_array_2(n))

    elif command == 3:
        arr = read_array()
        print("Result:", copy_array_1(arr))

    elif command == 4:
        arr = read_array()
        print("Result:", copy_array_2(arr))

    else:
        print("Wrong command try again")


