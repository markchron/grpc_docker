# Sample Python client that sends commands to a server
from __future__ import print_function

import logging
import grpc
import keyvalueunary_pb2
import keyvalueunary_pb2_grpc

TIMEOUT_SECONDS = 3

def set_value(stub, key, value):
    request = keyvalueunary_pb2.SetValueRequest(key=key, value=value)
    response = stub.SetValue(request, TIMEOUT_SECONDS)
    return response.value

def get_value(stub, key):
    request = keyvalueunary_pb2.GetValueRequest(key=key)
    response = stub.GetValue(request, TIMEOUT_SECONDS)
    return response.value

def count_value(stub, key):
    request = keyvalueunary_pb2.CountValueRequest(key=key)
    response = stub.CountValue(request, TIMEOUT_SECONDS)
    return response.count

def main():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = keyvalueunary_pb2_grpc.KeyValueUnaryStub(channel)

        #
        print('Running sample data ...')
        set_value(stub, 'foo', 'bar')
        set_value(stub, 'baz', 'anacoda is here')

        print(get_value(stub, 'foo'))
        print(count_value(stub, 'baz'))


if __name__ == '__main__':
    logging.basicConfig()
    main()