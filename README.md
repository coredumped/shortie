# Shortie

A minimalistic filesystem path shortener.

Usage:

```bash
shortie [PATH]
```

Shortens a filesystem path by displaying only a few characters
per path component.

 -h, --help     Display this help message

 -v, --version  Get version

 --home         Replace home directory with tilde (~)

 --no-home      Inverse of --home

 -n &lt;number>     Count of characters to print per path component

If no PATH is given shortie defaults to the current working directory.
