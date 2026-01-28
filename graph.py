import pandas as pd
import matplotlib.pyplot as plt
import sys
import os
import glob

if len(sys.argv) > 1:
    filename = sys.argv[1]
else:
    filename = input("Введите путь к CSV-файлу: ").strip()

try:
    data = pd.read_csv(filename, header=None)
except Exception as e:
    print(f"Ошибка при чтении файла: {e}")
    exit(1)

y_values = data.iloc[0, 1:].values
y_values = pd.to_numeric(y_values, errors='coerce')

x_rows = data.iloc[1:, 1:].values
x_labels = data.iloc[1:, 0].values

for file_path in glob.glob("plots/test*"):
    if os.path.isfile(file_path) and '_' in file_path and int(file_path.split('_')[1].split('.')[0])>len(x_rows):
        os.remove(file_path)

output_dir = "plots"
os.makedirs(output_dir, exist_ok=True)

for i, row in enumerate(x_rows):
    label = str(x_labels[i])
    x_values = pd.to_numeric(row, errors='coerce')
    plt.figure(figsize=(8, 6))
    plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title(label)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    save_path = os.path.join(output_dir, f"{label}.jpg")
    plt.savefig(save_path, format='jpg', dpi=300)
    plt.close()

plt.figure(figsize=(8, 6))
plt.xlabel("x")
plt.ylabel("y")
plt.title(label)
plt.grid(True, alpha=0.3)
plt.tight_layout()

for i, row in enumerate(x_rows):
    label = str(x_labels[i])
    x_values = pd.to_numeric(row, errors='coerce')
    plt.plot(x_values, y_values, marker='o', linestyle='-')

save_path = os.path.join(output_dir, f"test_0.jpg")
plt.savefig(save_path, format='jpg', dpi=300)
plt.close()