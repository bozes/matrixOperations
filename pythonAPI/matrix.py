import ctypes
import numpy as np

operators_dll = ctypes.CDLL('matrixOperations/MatrixVectorOperations/Debug/operations.dll')

operators_dll.MatrixNew.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_void_p]
operators_dll.MatrixNew.restypes = ctypes.c_void_p

operators_dll.MatrixGetElement.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int]
operators_dll.MatrixGetElement.restype = ctypes.c_float

operators_dll.AddFloatMatrix.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
operators_dll.AddFloatMatrix.restype = ctypes.c_void_p

operators_dll.SubFloatMatrix.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
operators_dll.SubFloatMatrix.restype = ctypes.c_void_p

operators_dll.MultiplyMatrixWithScalar.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_void_p]
operators_dll.MultiplyMatrixWithScalar.restype = ctypes.c_void_p

operators_dll.DivideMatrixWithScalar.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_void_p]
operators_dll.DivideMatrixWithScalar.restype = ctypes.c_void_p


class Matrix():
    def __init__(self, _array):
        self.array = _array
        self.rows = len(_array)
        self.cols = len(_array[0])
        self.obj = operators_dll.MatrixNew(len(_array), len(_array[0]), ctypes.c_void_p(np.ascontiguousarray(_array).ctypes.data))

    def __add__(self, other):
        result = np.ascontiguousarray(np.zeros((self.rows, self.cols), dtype=np.float32))
        operators_dll.AddFloatMatrix(self.obj, other.obj, result.ctypes.data)
        return result

    def __sub__(self, other):
        result = np.zeros((self.rows, self.cols), dtype=np.float32)
        operators_dll.SubFloatMatrix(self.obj, other.obj, result.ctypes.data)
        return result

    def __mul__(self, other):
        result = np.zeros((self.rows, self.cols), dtype=np.float32)
        operators_dll.MultiplyMatrixWithScalar(self.obj, ctypes.c_float(other), result.ctypes.data)
        return result

    def __truediv__(self, other):
        result = np.zeros((self.rows, self.cols), dtype=np.float32)
        operators_dll.DivideMatrixWithScalar(self.obj, ctypes.c_float(other), result.ctypes.data)
        return result

    def get_array(self):
        return self.array

    def get_element(self, index):
        return operators_dll.MatrixGetElement(self.obj, index)

    def get_rows(self):
        return operators_dll.MatrixGetRows(self.obj)

    def get_cols(self):
        return operators_dll.MatrixGetCols(self.obj)
