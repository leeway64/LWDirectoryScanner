from src.CBOR_Deserializer import CBOR_deserializer


class TestSuite:
    def test_CBOR_Deserializer(self):
        deserial = CBOR_deserializer("test.cbor")
        assert deserial.CBOR_file_name == "test.cbor"

        deserial.CBOR_file_name = "test1.cbor"
        assert deserial.CBOR_file_name == "test1.cbor"

    def test_0(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/0_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == 0
        assert summary["directories"] == 0
        assert summary["files"] == 0

    def test_b(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/b_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == 0
        assert summary["directories"] == 0
        assert summary["files"] == 2

    def test_c(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/c_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == 3
        assert summary["directories"] == 4
        assert summary["files"] == 2

    def test_test_dirs(self):
        deserial = CBOR_deserializer("src/test_deserializer/CBOR_test_files/test_dirs_summary.cbor")
        summary = deserial.deserialized_data

        assert summary["deepest_depth"] == 4
        assert summary["directories"] == 8
        assert summary["files"] == 5
