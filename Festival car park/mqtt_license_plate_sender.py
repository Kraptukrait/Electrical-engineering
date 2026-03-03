import paho.mqtt.client as mqtt

# -----------------------------
# MQTT Settings
# -----------------------------
broker = "BROKER_IP_ADDRESS"   # e.g. "192.168.0.100"
topic_base = "autos/"

# -----------------------------
# TXT file with license plates
# -----------------------------
txt_file = "license_plates.txt"

# -----------------------------
# Create MQTT client
# -----------------------------
client = mqtt.Client("LicensePlateSender")  
client.connect(broker, 1883, 60)

# -----------------------------
# Read license plates from TXT file
# -----------------------------
with open(txt_file, "r") as f:
    license_plate_list = [line.strip() for line in f if line.strip()]

# -----------------------------
# Send all license plates via MQTT (retained)
# -----------------------------
for i, license_plate in enumerate(license_plate_list):
    topic = f"{topic_base}{i+1}"
    client.publish(topic, license_plate, retain=True)
    print(f"Sent: {topic} -> {license_plate}")

client.disconnect()
print("Done! All license plates have been sent.")
