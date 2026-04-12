import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('sorting_times.csv')

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 7))

display_names = ['Selection Sort', 'Bubble Sort', 'Insertion Sort', 'Standard Sort']
actual_columns = ['Selection', 'Bubble', 'Insertion', 'StdSort']
colors = ['blue', 'red', 'green', 'purple']

for display, col, color in zip(display_names, actual_columns, colors):
    ax1.plot(df['Size'], df[col], 
             label=display, marker='o', linestyle='-', color=color, linewidth=2)

ax1.set_title('Sorting Time vs Array Size (Linear Scale)', fontsize=14)
ax1.set_xlabel('Array Size (n)', fontsize=12)
ax1.set_ylabel('Sorting Time (ms)', fontsize=12)
ax1.grid(True, linestyle='--', linewidth=0.5)
ax1.legend(fontsize=11)

for display, col, color in zip(display_names, actual_columns, colors):
    ax2.plot(df['Size'], df[col], 
             label=display, marker='o', linestyle='-', color=color, linewidth=2)

ax2.set_title('Sorting Time vs Array Size (Log Scale)', fontsize=14)
ax2.set_xlabel('Array Size (n)', fontsize=12)
ax2.set_ylabel('Sorting Time (ms)', fontsize=12)
ax2.set_xscale('log')
ax2.set_yscale('log')
ax2.grid(True, which='both', linestyle='--', linewidth=0.5)
ax2.legend(fontsize=11)

plt.tight_layout()
plt.savefig('sorting_time_comparison.png', dpi=300)
plt.show()
