import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rcParams

times = [0, 0.1, 0.3, 0.5]
colors = ['black', 'blue', 'green', 'red']

with open("result.txt") as f:
    content = f.read()

blocks = content.strip().split("t = ")[1:]

fig, ax = plt.subplots(figsize=(8,5))

for i, block in enumerate(blocks):
    lines = block.strip().split("\n")[1:]
    data = np.array([list(map(float, l.split())) for l in lines if l.strip()])
    x = data[:, 0]
    u = data[:, 1]
    ax.plot(x, u, color=colors[i], linewidth=2, label=f't = {times[i]}')

ax.set_xlabel('x', fontsize=13, fontweight='bold')
ax.set_ylabel('u', fontsize=13, fontweight='bold')
ax.set_title('1D Advection - Lax Wendroff', fontsize=14, fontweight='bold')

ax.grid(True, which='both', linestyle='--', linewidth=0.8, alpha=0.7)

for spine in ax.spines.values():
    spine.set_linewidth(2)

ax.tick_params(axis='both', which='major', labelsize=11, width=2, length=5)
for label in ax.get_xticklabels() + ax.get_yticklabels():
    label.set_fontweight('bold')

legend = ax.legend(fontsize=11, framealpha=1, edgecolor='black')
legend.get_frame().set_linewidth(2)
for text in legend.get_texts():
    text.set_fontweight('bold')

plt.tight_layout()
plt.savefig('result.png', dpi=150)
plt.show()
