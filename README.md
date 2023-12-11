# arduino-rfid-red-green

## Setup
After boot, authorized id is blank
- red and green LEDs flash once together, indicating successful boot with blank authId

Id of first scan is saved as the authId
- alternating red and green LED flashes indicate authId saved
- flashes in order: green, red, green, red, green

## Subsequent Scans
Subsequent scans compare to authId, saved from id of first scan
- If the id matches authId, green light flashes
- If the id matches authId, red light flashes
