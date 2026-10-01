# API & Password Detector

A simple C program that scans a text file and flags lines containing
hardcoded passwords, API keys, or tokens — before that file gets
committed to Git.

## 📌 Why we built this

Hardcoded secrets are one of the most common security mistakes in
real codebases. According to GitGuardian's *State of Secrets Sprawl
2026* report, **28.65 million** new secrets were found exposed on
public GitHub in 2025 alone — a 34% jump from the year before. Once a
secret is committed, it stays in the repo's history forever, even if
it's deleted later. Big tools like `gitleaks` and `truffleHog` solve
this at a company scale. We built a small version of the same idea —
one we fully understand — as a learning project.

## ✨ Features

- Scans any text file for hardcoded secrets
- Recognizes **45+ patterns**, including real key formats from AWS,
  GitHub, Google, Slack, Stripe, Anthropic, OpenAI, and more
- Case-insensitive — catches `password`, `Password`, and `PASSWORD`
  the same way
- Reports every match with its exact line number
- Lets you mark a specific line as safe to ignore
- Plain C, zero external libraries

## 🔍 What it detects

| Provider | Example prefix(es) |
|---|---|
| AWS | `AKIA`, `ASIA` |
| GitHub | `ghp_`, `gho_`, `ghs_`, `ghu_`, `ghr_` |
| Google | `AIza`, `GOCSPX-`, `ya29.` |
| Slack | `xoxb-`, `xoxp-`, `xapp-` |
| Stripe | `sk_live_`, `sk_test_`, `rk_live_` |
| Anthropic / OpenAI | `sk-ant-`, `sk-proj-` |
| Others | SendGrid, Shopify, DigitalOcean, Linear, npm, PyPI, JWT |
| Generic | `password`, `secret`, `api_key`, `token`, private key headers |

These aren't random guesses — most providers deliberately give their
keys a fixed, recognizable prefix, specifically so leak-scanners can
catch and auto-revoke them. We're checking for the same prefixes real
tools look for.

## ⚙️ How it works

1. You enter a filename in your directory when the program starts.
2. It reads the file one line at a time.
3. Each line is converted to lowercase, so capitalization doesn't
   matter.
4. The line is checked against our list of 45+ known secret patterns.
5. Any match is printed immediately, with the line number.
6. At the end, it prints a total count and exits with code `1` if
   anything was found, or `0` if the file was clean — the same signal
   Git checks when deciding whether to allow a commit.

## 🚀 Getting started

Requires `gcc` (or any C compiler). No external libraries needed.

```bash
gcc -o detector api-password-detector.c
./detector
```

## 🧪 Example

```
=== Simple Api and Password Detector ===
Enter the file name to scan: test_secrets.txt
[ALERT] Line 2: possible secret found (matched "akia")
[ALERT] Line 3: possible secret found (matched "ghp_")
[ALERT] Line 4: possible secret found (matched "xoxb-")
[ALERT] Line 5: possible secret found (matched "sk_test_")

Scanned 9 line(s).
RESULT: 8 possible secret(s) found. Commit should be BLOCKED.
```

Two test files are included: `secrets.txt` (should trigger
several alerts) and `clean.txt` (should pass with no alerts).

## ⚠️ Limitations

- Only catches secrets under a known keyword or prefix — an unusual
  variable name can slip through
- Checks one file per run, typed in manually
- Not yet wired into Git automatically

## 🔮 What's next
- we are going to make it more useful and more advance and you don't need to compile it every time you download it .
- we are going add some more features like it can access the entire computer like you just have to enter your file name thats it  
## 👥 Built by

Md Enaytullah Amir / Rohit Kumar
