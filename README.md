# Filtered Distortion AutoWah

This is a JUCE C++ implementation of some algorithms I came up with.

It distorts only certain frequency range(s), instead of the entire frequency range of the electric guitar. 

The usable frequency range of the electric guitar is between more or less 100 Hz and 8000 Hz. With this plugin, the output is clean, except for, say, a few hundred Hz above and below 800 Hz (Q factor, center frequency and gain are adjustable). I implemented three such adjustable frequency bands.

Why even try this? For one, because I was genuinely curious how it would sound. Secondly, because DSP makes it easy (compared to analog). 

How does it sound? At this point, not bad and not great. It most likely needs some additional filtering to eliminate aliasing distortion.

Each of the three adjustable frequency bands implements an IIR bandpass filter. The samples in this bandpass range get substracted from the input and distortion is applied to them. (TO DO: After this step, it needs the additional filtering to get rid of aliasing distortion). In the next step, this substracted and distorted range of samples gets added add back in. This achieves the goal of having an output with a certain frequency range distorted and everything above and below that range remains clean/unaffected.

The gain formulas are from the book <a href="https://www.amazon.com/Designing-Audio-Effect-Plugins-C/dp/1138591939/ref=sr_1_1?crid=33QAQWW40DDF3&keywords=will+pirkle&qid=1686975397&sprefix=will+pirkle%2Caps%2C158&sr=8-1&ufe=app_do%3Aamzn1.fos.006c50ae-5d4c-4777-9bc0-4513d670b6bc">Designing Audio Effect Plugins in C++: For AAX, AU, and VST3 with DSP Theory 2nd Edition</a>, by Will Pirkle. More precisely, the formulas are from his "Addendum_A19_Pirkle_v1.0.pdf", which I included in the repository. This is a fantastic treatise on digitally modeling the complex behavior of tubes in a guitar amplifier.

Hat tip to https://github.com/JanWilczek

I almost forgot... The Visual Studio solution also includes an autowah, which I added as an afterthought, since I already had the necessary bandpass filter implemented. It uses a sine wave for modulation. Generally, guitar players are not crazy about autowah, we prefer wah pedals that we can control entirely. I enjoyed much more writing the DSP part than using the autowah, but even a autowah has its place at times.
