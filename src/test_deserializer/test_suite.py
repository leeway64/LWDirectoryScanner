from src.CBOR_Deserializer import CBOR_deserializer

class TestSuite:
    def test_CBOR_Deserializer(self):
        cd = CBOR_deserializer("test.cbor")
        assert cd.CBOR_file_name == "test.cbor"
        cd.CBOR_file_name = "test1.cbor"
        assert cd.CBOR_file_name == "test1.cbor"
        
        cd.CBOR_file_name = r"src/test_deserializer/CBOR_test_files/test.cbor"
        assert cd.deserialized_data[42] == "Is the answer"
        assert cd.deserialized_data["Is CBOR awesome?"] == True
