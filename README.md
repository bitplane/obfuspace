# Obfuspace

Encode arbitrary data into whitespace!

## Because reasons

JSON doesn't support comments, so we can't put metadata into it without
changing the schema. This isn't usually a problem as that's flexible, but
if you want to embed metadata you change the data, which is icky.

So this is something even ickier! We can have a many space, tab, carriage
return and newlines as we like, and encode data into them.

But that's for some other time. This is a simple library and command line
app that can be used to encode data into whitespace.

## Hacking

Open vscode in the root of the project, you'll get a devcontainer
with all the trimmings.

Or do stuff manually if you like:

```bash
make
make test
```

## License

WTFPL with one additional clause:

1. Don't blame me.