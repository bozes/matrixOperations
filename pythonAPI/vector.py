import ctypes
import numpy as np

operators_dll = ctypes.CDLL('matrixOperations/MatrixVectorOperations/Debug/operations.dll')

operators_dll.VectorNew.argtypes = [ctypes.c_int, ctypes.c_void_p]
operators_dll.VectorNew.restypes = ctypes.c_void_p

operators_dll.VectorGetElement.argtypes = [ctypes.c_void_p, ctypes.c_int]
operators_dll.VectorGetElement.restype = ctypes.c_float

operators_dll.AddFloatVector.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
operators_dll.AddFloatVector.restype = ctypes.c_void_p

operators_dll.SubFloatVector.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
operators_dll.SubFloatVector.restype = ctypes.c_void_p

operators_dll.MultiplyVectorWithScalar.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_void_p]
operators_dll.MultiplyVectorWithScalar.restype = ctypes.c_void_p

operators_dll.DivideVectorWithScalar.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_void_p]
operators_dll.DivideVectorWithScalar.restype = ctypes.c_void_p


class Vector:
    def __init__(self, _array):
        self.array = _array
        self.size = len(_array)
        self.obj = operators_dll.VectorNew(len(_array),
                                           ctypes.c_void_p(np.ascontiguousarray(_array).ctypes.data))

    def __add__(self, other):
        result = np.zeros(self.size, dtype=np.float32)
        operators_dll.AddFloatVector(self.obj, other.obj, result.ctypes.data)
        return result

    def __sub__(self, other):
        result = np.zeros(self.size, dtype=np.float32)
        operators_dll.SubFloatVector(self.obj, other.obj, result.ctypes.data)
        return result

    def __mul__(self, other):
        result = np.zeros(self.size, dtype=np.float32)
        operators_dll.MultiplyVectorWithScalar(self.obj, ctypes.c_float(other), result.ctypes.data)
        return result

    def __truediv__(self, other):
        result = np.zeros(self.size, dtype=np.float32)
        operators_dll.DivideVectorWithScalar(self.obj, ctypes.c_float(other), result.ctypes.data)
        return result

    def get_array(self):
        return self.array

    def get_element(self, index):
        return operators_dll.VectorGetElement(self.obj, index)

    def get_size(self):
        return operators_dll.VectorGetSize(self.obj)



if __name__ == "__main__":
    v = Vector(np.array([1.0, 1.0]).astype(np.float32)
    v2 = Vector(np.array([2.0, 2.0]).astype(np.float32)
    print(v + v2)