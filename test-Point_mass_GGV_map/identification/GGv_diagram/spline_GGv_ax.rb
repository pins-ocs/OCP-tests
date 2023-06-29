#--------------------------------------------------------------------------#
#   ____        _ _               ____ _
#  / ___| _ __ | (_)_ __   ___   / ___| | __ _ ___ ___
#  \___ \| '_ \| | | '_ \ / _ \ | |   | |/ _` / __/ __|
#   ___) | |_) | | | | | |  __/ | |___| | (_| \__ \__ \
#  |____/| .__/|_|_|_| |_|\___|  \____|_|\__,_|___/___/
#        |_|
#   ____       _                ____  ____
#  / ___|  ___| |_ _   _ _ __   |___ \|  _ \
#  \___ \ / _ \ __| | | | '_ \    __) | | | |
#   ___) |  __/ |_| |_| | |_) |  / __/| |_| |
#  |____/ \___|\__|\__,_| .__/  |_____|____/
#                       |_|
#--------------------------------------------------------------------------#


include Mechatronix


mechatronix do |data|

    # Read the data files
    pars_th, table_th = Utils::read_from_table(File.expand_path('../ggv_spline_th.txt', __FILE__))
    pars_vx, table_vx = Utils::read_from_table(File.expand_path('../ggv_spline_vx.txt', __FILE__))
    pars_ax, table_ax = Utils::read_from_table(File.expand_path('../ggv_spline_ax.txt', __FILE__))

    ax = [table_ax["col_1"]]  # initialize
    for ii in 2..table_th["th"].length do
        ax << table_ax["col_" + ii.to_s]
    end


    data.SplineGGvAx = {
        :spline_type   => 'bicubic',
        # :transposed    => false,
        :make_y_closed => true,
        :xdata         => table_vx["vx"],
        :ydata         => table_th["th"],
        :zdata         => ax
    }

end

# EOF
