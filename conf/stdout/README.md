# Stdout handler

This handler can be used to post incoming mails to standard out. It has no following configuration options.

## Example configuration

```json
{
    "handlers": [{
        "username": "some_user",
        "password": "some_password",
        "handler": "stdout"
    }],
    "name": "thepieterdc.mailbridge.local",
    "port": 2525
}
```