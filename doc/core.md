

1. Description:

   Portable library independent of operating system and architecture, can be used for low-level development! Maybe it will be used by me for my own toy OS development in the future  :satisfied:  :satisfied:  :satisfied:  :satisfied: :pray: :pray::pray::pray:

2. Workspace:

   ```
   ├── doc									# ustl document
   ├── tests								# Unit testing for ustl
   │   └── third-party					# Third-party library support
   └── ustl									# ustl root directory
       ├── cmake							# cmake template configuration file
       ├── core							# submodule ustl::core
       │   ├── inc
       │   │   └── type					# C++ static type identification implement
       └── std								# submodule ustl::std, Depends on specific operating 																	 
                                    # system and architecture
   ```

3. To do:

   - [x] Intrusive Generic Containers.
   - [ ] General Algorithm.
   - [ ] Type Identification.
   - [ ] Conceptual Memory Allocator.
   - [ ] Stay Tuned.

