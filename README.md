# arduino-rfid-red-green

## Boot
red and green LEDs flash once together, indicating successful boot

After boot, authorized id is blank and waits for first scan

## Setting authId
Id of first scan is saved as the authId
- alternating red and green LED flashes indicate authId saved
- flashes in order, indicating successful scan: green, red, green, red, green

## Subsequent Scans
Subsequent scans compare scanned id to authId (authId saved from id of first scan)
- If the id matches authId, green light flashes
- If the id matches authId, red light flashes
