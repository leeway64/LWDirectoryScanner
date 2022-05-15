from src.CBOR_Deserializer import CBOR_deserializer


class TestSuite:
    def test_CBOR_Deserializer(self):
        deserial = CBOR_deserializer("test.cbor")
        assert deserial.CBOR_file_name == "test.cbor"

        deserial.CBOR_file_name = "test1.cbor"
        assert deserial.CBOR_file_name == "test1.cbor"

    def test_b(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/b_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == str(0)
        assert summary["directories"] == str(0)
        assert summary["files"] == str(2)

    def test_c(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/c_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == str(1)
        assert summary["directories"] == str(1)
        assert summary["files"] == str(2)

    def test_e(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/e_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == str(3)
        assert summary["directories"] == str(4)
        assert summary["files"] == str(4)

    def test_test_dirs(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/test_dirs_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == str(4)
        assert summary["directories"] == str(9)
        assert summary["files"] == str(10)
