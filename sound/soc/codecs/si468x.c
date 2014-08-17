/*
 * sound/soc/codecs/si468x.c -- Codec driver for SI468X chips
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 * Copyright (C) 2014 Bjoern Biesenbach
 *
 * Author: Bjoern Biesenbach <bjoern.biesenbach@gmail.com>
 * Based on si468x.c of Andrey Smirnov <andrew.smirnov@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/initval.h>

static unsigned int si468x_codec_read(struct snd_soc_codec *codec,
		unsigned int reg)
{
	return 0;
}

static int si468x_codec_write(struct snd_soc_codec *codec,
		unsigned int reg, unsigned int val)
{
	return 0;
}

static const struct snd_soc_dapm_widget si468x_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),
};

static const struct snd_soc_dapm_route si468x_dapm_routes[] = {
	{ "Capture", NULL, "LOUT" },
	{ "Capture", NULL, "ROUT" },
};

static int si468x_codec_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	return 0;
}

static int si468x_codec_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	int rate;

	rate = params_rate(params);
	if (rate != 48000) {
		dev_err(dai->codec->dev, "Rate: %d is not supported\n", rate);
		return -EINVAL;
	}
	return 0;
}

static int si468x_codec_probe(struct snd_soc_codec *codec)
{
	return 0;
}

static struct snd_soc_dai_ops si468x_dai_ops = {
	.hw_params	= si468x_codec_hw_params,
	.set_fmt	= si468x_codec_set_dai_fmt,
};

static struct snd_soc_dai_driver si468x_dai = {
	.name		= "si468x-hifi",
	.capture	= {
		.stream_name	= "Capture",
		.channels_min	= 2,
		.channels_max	= 2,

		.rates = 
			SNDRV_PCM_RATE_48000,
		.formats =
			SNDRV_PCM_FMTBIT_S16_BE
	},
	.ops		= &si468x_dai_ops,
};

static struct snd_soc_codec_driver soc_codec_dev_si468x = {
	.probe  = si468x_codec_probe,
	.read   = si468x_codec_read,
	.write  = si468x_codec_write,
	.dapm_widgets = si468x_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(si468x_dapm_widgets),
	.dapm_routes = si468x_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(si468x_dapm_routes),
};

static int si468x_platform_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_si468x,
			&si468x_dai, 1);
}

static int si468x_platform_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

MODULE_ALIAS("platform:si468x-codec");

static struct platform_driver si468x_platform_driver = {
	.driver		= {
		.name	= "si468x-codec",
		.owner	= THIS_MODULE,
	},
	.probe		= si468x_platform_probe,
	.remove		= si468x_platform_remove,
};
module_platform_driver(si468x_platform_driver);

MODULE_AUTHOR("Bjoern Biesenbach <bjoern@bjoern-b.de>");
MODULE_DESCRIPTION("ASoC Si468X codec driver");
MODULE_LICENSE("GPL");
