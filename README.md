# lk::msg
a message/signal libary for modern C++.

Requires C++ 17.

# How to use

## Building

### Universal guide

For specific Linux / Windows instructions, see below.

This project uses CMake.

1. Configure CMake. Useful options are:
  * `CMAKE_BUILD_TYPE`, which can either be `Debug` or `Release`.
  * `LK_MESSAGES_STATIC`, which should be `ON` for a static library build, and `OFF` (default) for a dynamic library build.
2. Build. The output folder is referred to as `$bin` in this guide.
3. Add the `include` folder to the include directories of your compiler/build system of choice, and `$bin` to your link directories.
4. Include `lk/messages.h` and link against `lkmsg`.

### Linux / Unix

This guide assumes you have basic knowledge of the terminal and assumes a shell like `sh`.

1. Run `cmake` with `-DCMAKE_BUILD_TYPE=Release`. You can specify `-DLK_MESSAGES_STATIC=ON` to build `lk::msg` as a static library. by default a dynamic library is built.
2. Run `make`.
3. You now have `liblkmsg.so` or `liblkmsg.a`, depending on whether `LK_MESSAGES_STATIC` was set in cmake. 
4. Add `include` to your build systems include paths
5. Add folder in which `make` was run to link paths.
6. Link against `lkmsg`, for example with `-llkmsg`.

### Windows

Use Visual Studio, CLion or other IDE that supports CMake projects. 
1. Open / Import this project. 
2. Configure CMake. Useful options are:
  * `CMAKE_BUILD_TYPE`, which can either be `Debug` or `Release`.
  * `LK_MESSAGES_STATIC`, which should be `ON` for a static library build, and `OFF` (default) for a dynamic library build.
3. Build.
4. The output folder now has the library `.dll` or `.lib` file, which you can link to. `include` should be added to include paths.

## Using lkmsg in your own project

In general, it is recommended that you `using namespace lk`, if `msg` does not conflict with other namespaces in your project.

`lk::msg` uses the following concepts: 

- Channel: Connects listeners to messages. This is the base of all communication in `lk::msg`. A Channel is instantiated like so:
```cpp
lk::msg::Channel::Ptr my_channel = lk::msg::Channel::create();
```
This creates a shared (refcounted) pointer to a channel. This is the only way to construct a Channel.


- Listener: Connects to a Channel to listen to new messages. Invokes a callback/handler on message receive.
```cpp
lk::msg::Listener my_listener(my_channel, my_handler);
```
Note that the constructor takes a `lk::msg::Channel::Ptr` by value. This ensures that the Channel is kept alive (through refcounting) as long as listeners exist.
`my_handler` is a function of signature `void(const lk::msg::Message&)`. You may pass `nullptr` for this and set the handler later via `my_listener.set_handler(my_handler);`.

- Message: A lightweight object encoding the type of message (as an `int`), and the message data with `std::any`.
```cpp
lk::msg::Message my_message(1, std::string("Hello, World!"));
my_channel.send(std::move(my_message));
```
Note that the message is moved into `Channel::send()` - this design is important as `lk::msg` is planned to be async later. Further, this clarifies that the channel now owns the message, and once its been sent to every listener, it will be destroyed.

The first argument, `1` in this case, is of type `int`. This is to be used, with an enum instead of a raw `int` for example, to identify what type of message it is, i.e. what its purpose is.
Note that, to identify which type is held by the `std::any` member `data`, `std::any::type` can be compared to `typeid(xyz)` to find out whether a cast from `data` to type `xyz` is valid. This `purpose` member of Message is useful because two different messages (like a hello and a goodbye message) could both have a string as data (i.e. `std::any::type`), yet be different kinds of messages which are to be handled differently. In this case, the `std::any::type` is the same, but the `Message::purpose` is not. 

- MultiListener: A single object managing multiple listeners to multiple channels, receiving all messages in a single handler. Can be used like a normal Listener, but will listen to multiple channels at the same time. If this finds frequent use, then Channels likely have not been used properly, and multiple channels can probably be merged into one. A MultiListener is useful for logging all ongoing messages in the program, but if its used for other things, there is likely an inefficient use of Channels.

