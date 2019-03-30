# Slack handler

The Slack handler can be used to send incoming mails to a Slack channel. It has the following configuration options:

- **channel:** The Slack channel where the incoming mails should be sent to.
- **webhook:** The webhook url to send the mails to, this can be obtained by creating a new Incoming Webhook configuration at the Slack website.

## Example configuration

```json
{
    "handlers": [{
        "username": "some_user",
        "password": "some_password",
        "handler": "slack",
        "options": {
            "channel": "some_channel_name",
            "webhook": "https://hooks.slack.com/services/sometext/somemoretext/evenmoretext"
        }
    }],
    "name": "thepieterdc.mailbridge.local",
    "port": 2525
}
```