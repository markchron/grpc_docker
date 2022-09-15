from grpc.beta import implementations

import stringdb_pb2

PORT = 50051
TIMEOUT_SECONDS = 3

def main():
    channel = implementations.insecure_channel('localhost', PORT)
    stub = stringdb_pb2.beta_create_StringDb_stub(channel)