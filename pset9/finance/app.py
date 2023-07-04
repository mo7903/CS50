import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Store the user in session's id
    id = session["user_id"]

    # Get the needed data from database
    temp = db.execute("SELECT cash FROM users WHERE id = :id", id = id)
    cash = temp[0]["cash"]
    shares = db.execute("SELECT * FROM shares WHERE id = ? AND nshares > 0", id)
    totalshares = 0
    for share in shares:
        totalshares += share.get("price")*share.get("nshares")

    return render_template("index.html", shares=shares, cash=cash, totalshares=totalshares)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Store the user in session's id
        id = session["user_id"]

        # Ensure Stock symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("you call that a stock symbol?!", 400)

        # Ensure valid number of shares
        if request.form.get("shares").isnumeric():
            shares = int(request.form.get("shares"))
        else:
            return apology("Positive integer shares only", 400)
        if shares < 1:
            return apology("Positive integer shares only", 400)

        stock = lookup(request.form.get("symbol"))
        cost = stock.get("price")*shares
        temp = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
        cash = temp[0]["cash"]

        # Ensure User has enough money for the purchase
        if cash < cost:
            return apology("Not Enough Money", 400)

        # Buy Stock shares if all is ok
        else:

            # Check if the user  bought shares in this stock before
            if db.execute("SELECT * FROM shares WHERE id = ? AND symbol = ?", id, stock.get("symbol")) == []:

                # Create row in database and update user's cash
                db.execute("INSERT INTO shares (id, symbol, nshares, price, name) VALUES (?, ?, ?, ?, ?)",
                            id, stock.get("symbol"), shares, stock.get("price"), stock.get("name"))
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - cost, id)
                db.execute("INSERT INTO history (id, symbol, nshares, price, time) VALUES (?, ?, ?, ?, ?)",
                            id, stock.get("symbol"), shares, stock.get("price"), datetime.now())
                return redirect("/")
            else:

                # Update number of shares and user's cash
                db.execute("UPDATE shares SET nshares = nshares + ?, price = ? WHERE id = ? AND symbol = ?",
                            shares, stock.get("price"), id, stock.get("symbol"))
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - cost, id)
                db.execute("INSERT INTO history (id, symbol, nshares, price, time) VALUES (?, ?, ?, ?, ?)",
                            id, stock.get("symbol"), shares, stock.get("price"), datetime.now())
                return redirect("/")


    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Store the user in session's id
    id = session["user_id"]

    # Get the needed data from database
    shares = db.execute("SELECT * FROM history WHERE id = ?", id)

    return render_template("history.html", shares=shares)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure Stock symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("you call that a stock symbol?!", 400)

        # Get Stock data and renders the quoted pag
        stock = lookup(request.form.get("symbol"))
        stockname = stock.get("name")
        price = usd(stock.get("price"))

        return render_template("quoted.html", stockname=stockname, price=price, symbol=request.form.get("symbol"))

    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username to see if it's unique
        if len(db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))) != 0:
            return apology("username already exists", 400)

        # PERSONAL TOUCH: checks that password is of minimum length and format
        #if len(request.form.get("password")) < 10:
            return apology("password req: >10 chars and contain >1 non-alphanumeric char", 400)

        # checks confirmation of password matches the original
        if request.form.get("password") == request.form.get("confirmation"):

            # hashes the password and inserts user into database
            hashed = generate_password_hash(request.form.get("password"))
            db.execute("INSERT INTO users (username, hash) VALUES (? , ?)", request.form.get("username"), hashed)
            temp = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            # Remember which user has logged in
            session["user_id"] = temp[0]["id"]

            # Redirect user to home page
            return redirect("/")

        else:
            return apology("Passwords Don't Match", 400)

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session["user_id"]
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check the Submitted Symbol
        temp = db.execute("SELECT * FROM shares WHERE id = ? AND symbol = ?", id, request.form.get("symbol"))
        if temp == []:
            return apology("Stock Not Found in your shares", 404)
        else:
            # Ensure valid number of shares
            shares = int(request.form.get("shares"))
            if shares < 1:
                return apology("Positive integer shares only", 400)

            # Ensure user has enough shares to sell
            elif temp[0]["nshares"] < shares:
                return apology("You can't sell what you don't have", 400)

            else:
                stock = lookup(request.form.get("symbol"))
                cost = stock.get("price")*shares
                cashlist = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
                cash = cashlist[0]["cash"]

                # Update number of shares and user's cash
                db.execute("UPDATE shares SET nshares = nshares - ?, price = ? WHERE id = ? AND symbol = ?",
                            shares, stock.get("price"), id, stock.get("symbol"))
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + cost, id)
                db.execute("INSERT INTO history (id, symbol, nshares, price, time) VALUES (?, ?, ?, ?, ?)",
                            id, stock.get("symbol"), -shares, stock.get("price"), datetime.now())
                return redirect("/")

    # Send Symbols of user's stock shares to UI of Sell
    symbols = db.execute("SELECT symbol FROM shares WHERE id = ? AND nshares > 0", id)
    return render_template("sell.html", symbols=symbols)