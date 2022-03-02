import cbor2

class CBOR_deserializer:
    def __init__(self, file_name=None):
        self._CBOR_file_name = file_name
        self._deserialized_data = None

    @property
    def deserialized_data(self):
        # Lazily load the deserialized data
        if self._deserialized_data:
            return self._deserialized_data
        else:
            self._deserialized_data = self.__deserialize()

    @property
    def CBOR_file_name(self):
        return self._CBOR_file_name

    @CBOR_file_name.setter
    def CBOR_file_name(self, new_file_name):
        self._CBOR_file_name = new_file_name

    def __deserialize(self):
        if self._CBOR_file_name:
            with open(self._CBOR_file_name, "rb") as file:
                deserial = cbor2.load(file)
                return deserial
        else:
            return None
