from io import BytesIO
# write_byte = BytesIO(b"\x00\x01\x00\x01\x00\x02\x00\x02\x00\x01\x00\x02")
write_byte = BytesIO(b"\x01\x00\x00\x00")
with open("test.bin","wb") as f:
    f.write(write_byte.getbuffer()) 