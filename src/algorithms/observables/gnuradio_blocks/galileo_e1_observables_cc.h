/*!
 * \file galileo_e1_observables_cc.h
 * \brief Interface of the observables computation block for Galileo E1
 * \author Mara Branzanti 2013. mara.branzanti(at)gmail.com
 * \author Javier Arribas 2013. jarribas(at)cttc.es
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */


#ifndef GNSS_SDR_GALILEO_E1_OBSERVABLES_CC_H
#define GNSS_SDR_GALILEO_E1_OBSERVABLES_CC_H


#include <fstream>
#include <string>
#include <gnuradio/block.h>


class galileo_e1_observables_cc;

typedef boost::shared_ptr<galileo_e1_observables_cc> galileo_e1_observables_cc_sptr;

galileo_e1_observables_cc_sptr
galileo_e1_make_observables_cc(unsigned int n_channels, bool dump, std::string dump_filename, int output_rate_ms, bool flag_averaging);

/*!
 * \brief This class implements a block that computes Galileo observables
 */
class galileo_e1_observables_cc : public gr::block
{
public:
    ~galileo_e1_observables_cc ();

    int general_work (int noutput_items, gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items, gr_vector_void_star &output_items);

private:
    friend galileo_e1_observables_cc_sptr
    galileo_e1_make_observables_cc(unsigned int nchannels, bool dump, std::string dump_filename, int output_rate_ms, bool flag_averaging);
    galileo_e1_observables_cc(unsigned int nchannels, bool dump, std::string dump_filename, int output_rate_ms, bool flag_averaging);

    //Tracking observable history
    std::vector<std::deque<double>> d_acc_carrier_phase_queue_rads;
    std::vector<std::deque<double>> d_carrier_doppler_queue_hz;
    std::vector<std::deque<double>> d_symbol_TOW_queue_s;

    // class private vars
    bool d_dump;
    bool d_flag_averaging;
    unsigned int d_nchannels;
    int d_output_rate_ms;
    std::string d_dump_filename;
    std::ofstream d_dump_file;
};

#endif
