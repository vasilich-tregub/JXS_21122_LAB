// JXS_SequenceEncoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <vector>
#include <time.h>
#include "libjxs.h"
extern "C" {
#include "cmdline_options.h"
#include "file_io.h"
#include "file_sequence.h"
#include "image_open.h"
}
#ifdef _DEBUG
#pragma comment(lib, "jxsd.lib")
#pragma comment(lib, "jxs_utils_d.lib")
#else
#pragma comment(lib, "jxs.lib")
#pragma comment(lib, "jxs_utils.lib")
#endif // DEBUG

#define DO_NOT_WRITE_JXS_SEQUENCE_OUTPUT_FILES

int main(int argc, char** argv)
{
	cmdline_options_t options;
	int optind;
	char* input_seq_n = NULL;
	char* output_seq_n = NULL;
	char* input_fn = NULL;
	char* output_fn = NULL;
	xs_config_t xs_config;
	xs_image_t image = { 0 };
	uint8_t* bitstream_buf = NULL;
	size_t bitstream_buf_size, bitstream_buf_max_size;
	xs_enc_context_t* ctx = NULL;
	int ret = 0;
	int file_idx = 0;

	std::string encode_durations("");

	if ((optind = cmdline_options_parse(argc, argv, CMDLINE_OPT_ENCODER, &options)) < 0)
	{
		ret = -1;
		return ret;
	}

	if (argc - optind != 2)
	{
		fprintf(stderr, "\nSingle image: %s [options] <image_in.ppm> <output.jxc>\n", argv[0]);
		fprintf(stderr, "\nFor sequences: %s [options] <sequence_in_%%06d.ppm> <sequence_out_%%06d.jxc>\n\n", argv[0]);
		fprintf(stderr, "Options:\n");
		cmdline_options_print_usage(CMDLINE_OPT_ENCODER);
		ret = -1;
		return ret;
	}

	xs_config.verbose = options.verbose;

	input_seq_n = argv[optind];
	output_seq_n = argv[optind + 1];

	input_fn = (char*) malloc(strlen(input_seq_n) + MAX_SEQ_NUMBER_DIGITS);
	output_fn = (char*) malloc(strlen(output_seq_n) + MAX_SEQ_NUMBER_DIGITS);

	sequence_get_filepath(input_seq_n, input_fn, file_idx + options.sequence_first);
	if (image_open_auto(input_fn, &image, options.width, options.height, options.depth) < 0)
	{
		fprintf(stderr, "Unable to open image %s!\n", input_fn);
		ret = -1;
		return ret;
	}

	if (!xs_config_parse_and_init(&xs_config, &image, options.xs_config_string, sizeof(options.xs_config_string) - 1))
	{
		fprintf(stderr, "Error in XS config\n");
		ret = -1;
		return ret;
	}

	if (xs_config.bitstream_size_in_bytes == 0)
	{
		// Specify 3.0 bpp by default (if nothing was specified).
		xs_config.bitstream_size_in_bytes = (size_t)(3.0 * image.width * image.height / 8);
	}

	if (!xs_enc_preprocess_image(&xs_config, &image))
	{
		fprintf(stderr, "Error preprocessing the image\n");
		ret = -1;
		return ret;
	}

	ctx = xs_enc_init(&xs_config, &image);
	if (!ctx)
	{
		fprintf(stderr, "Unable to allocate encoding context\n");
		ret = -1;
		return ret;
	}

	if (xs_config.bitstream_size_in_bytes == (size_t)-1)
	{
		// Take the RAW image size and add some extra for margin.
		bitstream_buf_max_size = image.width * image.height * image.ncomps * ((image.depth + 7) >> 3) + 1024 * 1024;
	}
	else
	{
		bitstream_buf_max_size = (xs_config.bitstream_size_in_bytes + 7) & (~0x7);
	}
	bitstream_buf = (uint8_t*) malloc(bitstream_buf_max_size);
	if (!bitstream_buf)
	{
		fprintf(stderr, "Unable to allocate codestream mem\n");
		ret = -1;
		return ret;
	}

	if (options.dump_xs_cfg > 0)
	{
		char dump_str[1024];
		memset(dump_str, 0, 1024);
		if (!xs_config_dump(&xs_config, &image, dump_str, 1024, options.dump_xs_cfg))
		{
			fprintf(stderr, "Unable to dump configuration for codestream (%s)\n", input_fn);
			ret = -1;
			return ret;
		}
		fprintf(stdout, "Configuration: \"%s\"\n", dump_str);
	}
	clock_t start = clock();
	do
	{
		if (!xs_enc_image(ctx, file_idx, &image, (uint8_t*)bitstream_buf, bitstream_buf_max_size, &bitstream_buf_size))
		{
			fprintf(stderr, "Unable to encode image %s\n", input_fn);
			ret = -1;
			break;
		}
		xs_free_image(&image);
		encode_durations += std::to_string(clock() - start) + " ";
#ifndef DO_NOT_WRITE_JXS_SEQUENCE_OUTPUT_FILES
		sequence_get_filepath(output_seq_n, output_fn, file_idx + options.sequence_first);
		if (!fileio_writable(output_fn))
		{
			fprintf(stderr, "Output file is not writable %s\n", output_fn);
			ret = -1;
			break;
		}
		if (is_sequence_path(input_seq_n) || is_sequence_path(output_seq_n))
		{
			fprintf(stderr, "writing %s\n", output_fn);
		}
		if (fileio_write(output_fn, bitstream_buf, bitstream_buf_size) < 0)
		{
			fprintf(stderr, "Unable to write output encoded codestream to %s\n", output_fn);
			ret = -1;
			break;
		}
#endif
		if (!(is_sequence_path(input_seq_n) || is_sequence_path(output_seq_n)))
		{
			break;
		}
		file_idx++;
		if ((options.sequence_n > 0) && (file_idx >= options.sequence_n))
		{
			break;
		}
		sequence_get_filepath(input_seq_n, input_fn, file_idx + options.sequence_first);
		if (!fileio_exists(input_fn))
		{
			break;
		}
		if ((ret = image_open_auto(input_fn, &image, options.width, options.height, options.depth)) < 0)
		{
			fprintf(stderr, "Unable to open image %s!\n", input_fn);
			ret = -1;
			break;
		}
		start = clock();
		if (!xs_enc_preprocess_image(&xs_config, &image))
		{
			fprintf(stderr, "Error preprocessing the image\n");
			ret = -1;
			break;
		}
	} while (ret == 0);

	// Cleanup.
	if (input_fn)
	{
		free(input_fn);
	}
	if (output_fn)
	{
		free(output_fn);
	}
	xs_free_image(&image);
	if (ctx)
	{
		xs_enc_close(ctx);
	}
	if (bitstream_buf)
	{
		free(bitstream_buf);
	}

	printf("%s\n", (char*)encode_durations.c_str());

	return ret;
}
