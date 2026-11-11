# T-Tree v3.1: Automated T-Stick serial configurer using `idmil-puara-serial-library`

## Build From Source

**Requirements: Git, CMake

Run the following in your terminal:

```bash
git clone git@github.com:foobiane/T-Tree-v3-1.git
cd T-Tree-v3-1
git submodule update --init --recursive
cmake -B Builds
cmake --build Builds
```

## Using the Interface

*This guide mainly applies to users of the physical interface housed at the IDMIL.*

* To SSH into the T-Tree, connect to the same network as the T-Tree (usually Mappings_net) and run on your machine: `ssh ttree3@ttree3.local`. The password is located inside the box.
* The T-Tree software runs from `~/ttree3/T-Tree v3.1/Builds` via a symlink at `~/ttree3/ttree3`. There is a shell script, `~/autostart.sh`, that starts the T-Tree software when the Raspberry Pi is powered on.

## Additional Files

* `patches`: Pure Data patches used for T-Tree v3.1 exhibitions
* `cad`: CAD STEP files for the T-Tree v3.1 case (created using OnShape)
