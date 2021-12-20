#!/usr/bin/env ruby
############################################################################
#                                                                          #
#  file: AlpRider_ffi_structs.rb                                           #
#                                                                          #
#  version: 1.0   date 20/12/2021                                          #
#                                                                          #
#  Copyright (C) 2021                                                      #
#                                                                          #
#      Enrico Bertolazzi and Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      Via Mesiano 77, I-38050 Trento, Italy                               #
#      email: enrico.bertolazzi@ing.unitn.it                               #
#             francesco.biral@ing.unitn.it                                 #
#             paolo.bosetti@ing.unitn.it                                   #
#                                                                          #
############################################################################

module AlpRider

  typedef :double, :data_t
  typedef :uint32, :index_t
  typedef :int,    :retcode

  class AlpRider_solver_params < FFI::Struct
    layout(
      :max_iter,             :index_t,
      :max_step_iter,        :index_t,
      :max_accumulated_iter, :index_t,
      :tolerance,            :data_t,
    )
    def initialize
      self[:max_iter]      = 500
      self[:max_step_iter] = 20
      self[:tolerance]     = 1e-10
    end
  end

  class AlpRider_model_params < FFI::Struct
    layout(

      :W,     :data_t,

      :W0,    :data_t,

      :W1,    :data_t,

      :epsi0, :data_t,

      :epsi1, :data_t,

      :tol0,  :data_t,

      :tol1,  :data_t,

      :y1_f,  :data_t,

      :y1_i,  :data_t,

      :y2_f,  :data_t,

      :y2_i,  :data_t,

      :y3_f,  :data_t,

      :y3_i,  :data_t,

      :y4_f,  :data_t,

      :y4_i,  :data_t,

    )

    def initialize
      members.each { |m| self[m] = Float::NAN }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class AlpRider_BC_params < FFI::Struct
    layout(

      :initial_y1, :bool,

      :initial_y2, :bool,

      :initial_y3, :bool,

      :initial_y4, :bool,

      :final_y1,   :bool,

      :final_y2,   :bool,

      :final_y3,   :bool,

      :final_y4,   :bool,

    )

    def initialize
      members.each { |m| self[m] = true }
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  class AlpRider_constraints_params < FFI::Struct
    layout(
      # 1D constraints
      :YboundSubType,   :index_t,
      :YboundEpsilon,   :data_t,
      :YboundTolerance, :data_t,

      # 2D constraints

      # Controls
    )

    def initialize
      members.each do |m|
        case self[m]
        when Float
          self[m] = Float::NAN
        when Fixnum
          self[m] = 0
        when FFI::Pointer
          self[m] = nil
        else
          warn "Unmanaged initialization type in struct (for field #{m} of type #{self[m].class})"
        end
      end
      # Custom initializations go here:
      # self[:key] = value
    end
  end

  attach_function :setup_model, # ruby name
                  :AlpRider_setup_model, # C name
                  [:pointer ,:pointer ,:pointer ],
                  :void

  attach_function :setup_solver, # ruby name
                  :AlpRider_setup_solver, # C name
                  [:pointer ],
                  :void

  attach_function :write_solution_to_file, # ruby name
                  :AlpRider_write_solution_to_file, # C name
                  [:string],
                  :void

  attach_function :printout_enabled?, # ruby name
                  :AlpRider_printout_is_enabled, # C name
                  [],
                  :int

  attach_function :enable_printout, # ruby name
                  :AlpRider_enable_printout, # C name
                  [],
                  :void

  attach_function :disable_printout, # ruby name
                  :AlpRider_disable_printout, # C name
                  [],
                  :void

  attach_function :reset_multiplier, # ruby name
                  :AlpRider_reset_multiplier, # C name
                  [],
                  :void

  attach_function :reset_BC_multiplier, # ruby name
                  :AlpRider_reset_BC_multiplier, # C name
                  [],
                  :void

  attach_function :set_internal_guess, # ruby name
                  :AlpRider_set_internal_guess, # C name
                  [],
                  :void

end

# EOF: AlpRider_ffi_stucts.rb
