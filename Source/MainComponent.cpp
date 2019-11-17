/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);

    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        setAudioChannels (0, 2);
    }
    
    //levelSlider.setRange(0.0, 0.25);
    //levelSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
    //addAndMakeVisible(levelSlider);
    //levelLabel.setText("Noise Level", dontSendNotification);
    //levelLabel.attachToComponent(&levelSlider, true);
    //addAndMakeVisible(levelLabel);
    
    
    lvl_l_sli.setRange(0.0, 0.25);
    lvl_r_sli.setRange(0.0, 0.25);
    lvl_l_sli.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
    lvl_r_sli.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
    addAndMakeVisible(lvl_l_sli);
    addAndMakeVisible(lvl_r_sli);
    
    lvl_l_lbl.setText("Left Level", dontSendNotification);
    lvl_r_lbl.setText("Right Level", dontSendNotification);
    lvl_l_lbl.attachToComponent(&lvl_l_sli, true);
    lvl_r_lbl.attachToComponent(&lvl_r_sli, true);
    addAndMakeVisible(lvl_l_lbl);
    addAndMakeVisible(lvl_r_lbl);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    //auto level = (float)levelSlider.getValue();
    //for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
    //    auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
    //    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
    //        auto noise = random.nextFloat() * 2.0f - 1.0f;
    //        buffer[sample] = noise * level;
    //    }
    //}
    
    //More optimised dsp
    //auto level = (float)levelSlider.getValue();
    //auto levelScale = level * 2.0f;
    //for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
    //    auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
    //    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
    //        auto noise = random.nextFloat();
    //        buffer[sample] = noise * levelScale - level;
    //    }
    //}
    
    //Independent control of  left and right channels
    auto lvl_l_val = (float)lvl_l_sli.getValue();
    auto lvl_r_val = (float)lvl_r_sli.getValue();
    auto lvl_l_scale = lvl_l_val * 2.0f;
    auto lvl_r_scale = lvl_r_val * 2.0f;
    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
            auto noise = random.nextFloat();
            if (channel == 0) {
                buffer[sample] = noise * lvl_l_scale - lvl_l_val;
            } else {
                buffer[sample] = noise * lvl_r_scale - lvl_r_val;
            }
        }
    }
}

void MainComponent::releaseResources()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    lvl_l_sli.setBounds(100, 10, getWidth()-120, 30);
    lvl_r_sli.setBounds(100, 40, getWidth()-120, 30);
}
