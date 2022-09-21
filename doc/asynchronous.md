
# Synchronous 
Blocking synchronous call: client must wait to get the response (or acknowlegement) that the request is completed. 


# Asynchronous
Using asynchronous messaging and request-response pattern, we remove the temporal coupling and have each service work independently. 

Using non-blocking asynchronous messaging, none of the services must available when an order is placed. They are all working independently processing messages in isolation.

The asynchronous request-response pattern allows you to tell a sender that the message has been processed and what the outcome or result was. You can leverage this to then build workflows to involve many different services all in a non-blocking way.