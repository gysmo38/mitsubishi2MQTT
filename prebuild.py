Import("env")

# Set the built firmware binary to the correct name.
binary_name = env.GetProjectOption("binary_name")
env.Replace(PROGNAME=binary_name)

# Allow the name of the binary to be reported by the webapp
env.Append(CPPDEFINES=[
  ("PIO_BINARY", binary_name)
])

