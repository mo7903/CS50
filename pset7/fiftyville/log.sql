-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check the crime scene reports of Humphrey Street at the date of the crime
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND year = 2021 AND month = 7 AND day = 28;
-- Shows that the theft of CS50 Duck took place at 10:15 AM & there were 3 Witnesses who mentioned the bakery

-- Get the 3 interviews that mentioned the bakery on the day of the crime
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- Ruth says that 10 minutes after the crime, he saw the thief get into a car in the bakery parking lot and drive away
-- Eugene says he recognized the thief after seeing him/her withdrawing money from the ATM at Leggett Street
-- Raymond says he heard the thief call someone for less than a minute to book the earliest flight ticket for him/her to leave tomorrow

-- Get all license plates that left the parking lot within half an hour after the crime
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit";

-- Get all account numbers that withdrew money at the day of the crime at Leggett Street
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- Get all caller id of calls less than a minute on the day of the crime
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28;

-- Connects tables (people, bank acounts, and atm transactions) to get the data of the people who withdrew money
SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
);

-- finds the people who match all criteria (license plate leaving the bakery after the crime, caller id making a call less than one minute, and bank account withdrawal) using multiple tables
SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
)
AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit")
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60);

-- Checks the passport number assosciated with a flight ticket leaving one day after the crime from the the final 3 suspects
SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")
AND year = 2021 AND month = 7 AND day = 29;

-- Checks who is leaving on the earliest flight
SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
)
AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit")
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")
AND year = 2021 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20));
-- Diana is not leaving on the earliest flight

-- Gets the time Taylor arrived at the bakery (8:34 AM) and left (10:35 AM)
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND license_plate = "1106N58";
-- Taylor left the bakery more than 10 minutes after the crime, so Ruth could not have heard her

-- Gets the time Bruce arrived at the bakery (8:23 AM) and left (10:18 AM)
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND license_plate = "94KL13X";
-- Bruce exited the bakery aroumd the time of the crime

-- Gets the time Diana arrived at the bakery (8:36 AM) and left (10:23 AM)
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND license_plate = "322W7JE";

-- Bruce is the Thief

-- Finds who called Bruce at the date of the crime
SELECT name FROM people WHERE phone_number =
(SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
AND caller = (SELECT phone_number FROM people WHERE name = "Bruce"));
-- The Accomplice is Robin

-- Finds the destination of the flight Diana took one day after the crime
SELECT city FROM airports WHERE id =
(SELECT destination_airport_id FROM flights
WHERE year = 2021 AND month = 7 AND day = 29
AND id =
(SELECT flight_id FROM passengers WHERE passport_number =
(SELECT passport_number FROM people WHERE name = "Bruce")));

-- Well, to begin with, the testimonies of the 3 witnesses were taken into account, showing that the thief left the bakery parking lot in a car around 10 minutes after the crime.
-- The thief was talking on the phone with someone telling that person to purchase the earliest flight ticket out of fiftyville for the day after the crime.
-- One of the witnesses stated having seen the thief withdrawing money from an ATM machine on Leggett Street on the morning of the crime.
-- It wasn't particularly difficult looking into the databases of the ATM record on July 28th, account numbers of all Fiftyville banks, license plates of the cars leaving the bakery at the time of the crime.
-- At this point, we had a promising list of 3 suspects (Taylor, Bruce, or Diana), but what was it that would make the murderer jump out?
-- Actually, two things, the first being the timing of exit from the bakery parking lot. The thief must have left around the time of 10:15 to 10:30, or Ruth might not have seen them.
-- The second being time of the flight: it must be the first flight out of fiftyville on July 29th.
-- Using a simple elimination technique as Taylor left the bakery at 10:35, well after Ruth had heard the thief, and Diana having her flight outside of fiftyville later than the first flight, the thief, it appears to me, must be Bruce.
-- After that, it was more than easy to find that Bruce's earliest flight out of Fiftyville was going to New York City, and the only call he made that day under one minute was to his accomplice who purchased the ticket and who happens to be so conically named Robin.
-- This, my dear watson, is what I surmised from the case at Fiftyville.