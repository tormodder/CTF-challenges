import base64
import gzip
import shutil
import lzma

def puzzleMaker(input_file_path, output_base64_path):

    with open(input_file_path, 'rb') as input_file:
        binary_data = input_file.read()

    # Compress the binary data using LZMA compression algorithm
    compressed_data = lzma.compress(binary_data)

    # Encode the compressed file to Base64
    base64_data = base64.b64encode(compressed_data)

    with open(output_base64_path, 'wb') as base64_file:
        base64_file.write(base64_data)

