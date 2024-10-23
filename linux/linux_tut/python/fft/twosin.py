#from sin import generate_sine_wave
import sin_func as sin_f
from scipy.io.wavfile import write
from scipy.fft import fft, fftfreq
from scipy.fft import rfft, rfftfreq
from scipy.fft import irfft
_, nice_tone = sin_f.generate_sine_wave(400, sin_f.SAMPLE_RATE, sin_f.DURATION)
_, noise_tone = sin_f.generate_sine_wave(4000, sin_f.SAMPLE_RATE, sin_f.DURATION)

noise_tone = noise_tone * 0.3
mixed_tone = nice_tone + noise_tone
normalized_tone = sin_f.np.int16((mixed_tone / mixed_tone.max()) * 32767)

#sin_f.plt.plot(normalized_tone[:1000])
#sin_f.plt.show()
#write("mysinewave.wav", sin_f.SAMPLE_RATE, normalized_tone)

# число точек в normalized_tone
N = sin_f.SAMPLE_RATE * sin_f.DURATION

#yf = fft(normalized_tone)
#xf = fftfreq(N, 1 / sin_f.SAMPLE_RATE)
yf = rfft(normalized_tone)
xf = rfftfreq(N, 1 / sin_f.SAMPLE_RATE)

# Максимальная частота составляет половину частоты дискретизации
points_per_freq = len(xf) / (sin_f.SAMPLE_RATE / 2)

# Наша целевая частота - 4000 Гц
target_idx = int(points_per_freq * 4000)

yf[target_idx-2:target_idx+2] = 0

new_sig = irfft(yf)

sin_f.plt.plot(new_sig[:1000])
sin_f.plt.show()

norm_new_sig = sin_f.np.int16(new_sig * (32767 / new_sig.max()))
write("clean.wav", sin_f.SAMPLE_RATE, norm_new_sig)

#sin_f.plt.plot(xf, sin_f.np.abs(yf))
#sin_f.plt.show()
