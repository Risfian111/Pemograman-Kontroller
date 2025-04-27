import pandas as pd

# Data for control and safety systems
data = {
    "Sistem": [
        "Level Transmitter (LT) - Storage Tank", 
        "Pressure Transmitter (PT) - Crusher Inlet", 
        "Vibration Sensor (VS) - Crusher Unit", 
        "Motor Current Sensor (MCS) - Conveyor & Crusher", 
        "Flow Sensor (FS) - Conveyor Output", 
        "Emergency Stop (E-STOP)", 
        "Dust Collector & Ventilation Fan", 
        "Overload Protection - Crusher & Motor", 
        "Alarm System (Horns & Beacons)", 
        "Interlock System", 
        "Sistem Kontrol Otomatis"
    ],
    "Fungsi": [
        "Mengukur ketinggian limestone dalam tangki penyimpanan", 
        "Mendeteksi tekanan masuk ke dalam crusher", 
        "Mendeteksi getaran abnormal pada mesin", 
        "Memonitor arus listrik motor penggerak", 
        "Mengukur laju massa limestone yang bergerak di conveyor", 
        "Mematikan sistem secara total saat kondisi darurat", 
        "Menangani debu limestone yang berbahaya bagi operator dan lingkungan", 
        "Melindungi mesin dari beban berlebih", 
        "Memberikan peringatan visual dan suara saat parameter di luar batas aman", 
        "Menjaga urutan operasi logis dan aman", 
        "Terhubung ke PLC (Programmable Logic Controller) dan HMI (Human Machine Interface)"
    ],
    "Kontrol": [
        "Jika level terlalu tinggi → conveyor berhenti otomatis", 
        "Jika tekanan terlalu tinggi → sinyal alarm dan shutdown otomatis", 
        "Jika getaran melebihi batas → unit mati otomatis (trip)", 
        "Jika arus terlalu tinggi → indikasi overloading → shutdown preventif", 
        "Mengatur kecepatan conveyor untuk menjaga feed rate tetap stabil", 
        "Mematikan sistem secara total saat kondisi darurat", 
        "Menangani debu berbahaya untuk mencegah kontaminasi dan risiko ledakan debu", 
        "Mengaktifkan sistem shutdown atau mengalihkan beban", 
        "Memberikan peringatan visual dan suara saat parameter di luar batas aman", 
        "Mencegah penumpukan material dengan mengatur urutan operasi", 
        "Operator bisa melihat data level, tekanan, getaran, dan status motor dari ruang kontrol"
    ],
    "Bahaya Dicegah": [
        "Overflow dan penumpukan material yang bisa menyebabkan macet atau tumpahan", 
        "Overload crusher yang bisa merusak peralatan", 
        "Kerusakan mekanik dan risiko kecelakaan operator", 
        "Kerusakan motor dan risiko kebakaran karena beban lebih", 
        "Ketidakseimbangan supply dan potensi lonjakan proses", 
        "Kecelakaan darurat yang bisa menyebabkan kerusakan besar", 
        "Penyakit paru, kontaminasi area kerja, risiko ledakan debu", 
        "Beban berlebih pada mesin yang dapat merusak peralatan", 
        "Kerusakan sistem dan kecelakaan akibat parameter yang berbahaya", 
        "Kecelakaan operasional yang disebabkan oleh urutan operasi yang tidak logis", 
        "Pengawasan real-time untuk mencegah kecelakaan dan kerusakan"
    ]
}

# Create a DataFrame
df = pd.DataFrame(data)

# Output to Excel
file_path = "/mnt/data/sistem_kontrol_dan_safety.xlsx"
df.to_excel(file_path, index=False)

file_path
