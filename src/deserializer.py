import cbor2

input_file = r""

obj = None

with open(input_file, "rb") as file:
    obj = cbor2.load(file)

print(obj)
