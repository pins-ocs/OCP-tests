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
    pars_ay, table_ay = Utils::read_from_table(File.expand_path('../ggv_spline_updown_ay.txt', __FILE__))
    pars_vx, table_vx = Utils::read_from_table(File.expand_path('../ggv_spline_updown_vx.txt', __FILE__))
    pars_ax, table_ax = Utils::read_from_table(File.expand_path('../ggv_spline_up_ax.txt', __FILE__))

    ax = [table_ax["col_1"]]  # initialize
    for ii in 2..table_ay["ay"].length do
        ax << table_ax["col_" + ii.to_s]
    end


    data.SplineGGvUp = {
        :spline_type   => 'bicubic',
        # :make_y_closed => true,
        :xdata         => table_vx["vx"],
        :ydata         => table_ay["ay"],
        :zdata         => ax,
        :boundary      => [
            {:closed => false, :extend => true, :extend_constant => true}
        ]
    }

end

# EOF
